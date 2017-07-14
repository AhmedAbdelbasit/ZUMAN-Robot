package UserInterface;

import SSH.SSHApplication;
import javafx.application.Platform;
import javafx.beans.property.ObjectProperty;
import javafx.embed.swing.SwingFXUtils;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.image.*;

import org.opencv.core.Mat;
import org.opencv.videoio.VideoCapture;

import javafx.event.ActionEvent;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class MannedMode {

    @FXML
    private Button camera_btn;

    @FXML
    private Button connect_btn;

    @FXML
    private ImageView frame;

    private SSHApplication sshApplication = null;

    private ScheduledExecutorService timer;

    private boolean cameraActive = false;

    private static int cameraId = 0;
    private static String videoIp = "http://192.168.1.107:8080/video?dummy=param.mjpg";

    private VideoCapture camera = new VideoCapture();

    public void initialize() {
        this.sshApplication = new SSHApplication();
    }

    public void startCamera(ActionEvent event) {
        if (!this.cameraActive) {
            this.camera.open(videoIp);

            if (this.camera.isOpened()) {
                this.cameraActive = true;

                Runnable frameGrabber = () -> {
                    Mat currentFrame = grabFrame();
                    Image imgToView = mat2Image(currentFrame);
                    updateImageView(frame, imgToView);
                };

                this.timer = Executors.newSingleThreadScheduledExecutor();
                this.timer.scheduleAtFixedRate(frameGrabber, 0, 33, TimeUnit.MILLISECONDS);

                this.camera_btn.setText("Stop Camera");
            } else {
                // log the error
                System.err.println("Impossible to open the camera connection...");
            }
        } else {
            // the camera is not active at this point
            this.cameraActive = false;
            // update again the button content
            this.camera_btn.setText("Start Camera");

            // stop the timer
            this.setClosed();
        }
    }

    public void startConnection(ActionEvent event) {
        String btn_txt = this.connect_btn.getText();

        if (btn_txt.contains("Start")) {
            this.sshApplication = new SSHApplication();

            this.sshApplication.executeCommand("sudo chown grad /dev/ttyUSB0");
            this.sshApplication.executeCommand("123456789");
            this.sshApplication.executeCommand("roscore &");
            this.sshApplication.executeCommand("rosrun rosserial_python serial_node.py tcp __name:=\"stick_node\" &");
            this.sshApplication.executeCommand("rosrun rosserial_python serial_node.py /dev/ttyUSB0 __name:=\"hw_node\"");

            this.connect_btn.setText("Stop Connection");
        } else if (btn_txt.contains("Stop")) {
            this.sshApplication.exit();

            this.connect_btn.setText("Start Connection");
        }
    }

    private Mat grabFrame() {
        Mat frame = new Mat();

        if (this.camera.isOpened()) {
            try {
                this.camera.read(frame);
                /* if (!frame.empty()) {
                    Imgproc.cvtColor(frame, frame, Imgproc.COLOR_BGR2GRAY);
                } */
            } catch (Exception e) {
                System.err.println("Error during frame elaboration: " + e);
            }
        }

        return frame;
    }

    private void updateImageView(ImageView view, Image image) {
        onFXThread(view.imageProperty(), image);
    }

    private static Image mat2Image(Mat frame) {
        try {
            return SwingFXUtils.toFXImage(matToBufferedImage(frame), null);
        }
        catch (Exception e) {
            System.err.println("Cannot convert the Mat obejct: " + e);
            return null;
        }
    }

    private static BufferedImage matToBufferedImage(Mat original) {
        // init
        BufferedImage image = null;
        int width = original.width(), height = original.height(), channels = original.channels();
        byte[] sourcePixels = new byte[width * height * channels];
        original.get(0, 0, sourcePixels);

        if (original.channels() > 1) {
            image = new BufferedImage(width, height, BufferedImage.TYPE_3BYTE_BGR);
        }
        else {
            image = new BufferedImage(width, height, BufferedImage.TYPE_BYTE_GRAY);
        }

        final byte[] targetPixels = ((DataBufferByte) image.getRaster().getDataBuffer()).getData();
        System.arraycopy(sourcePixels, 0, targetPixels, 0, sourcePixels.length);

        return image;
    }

    private static <T> void onFXThread(final ObjectProperty<T> property, final T value) {
        Platform.runLater(() -> {
            property.set(value);
        });
    }

    private void stopAcquisition() {
        if (this.timer != null && !this.timer.isShutdown()) {
            try {
                // stop the timer
                this.timer.shutdown();
                this.timer.awaitTermination(33, TimeUnit.MILLISECONDS);
            }
            catch (InterruptedException e) {
                // log any exception
                System.err.println("Exception in stopping the frame capture, trying to release the camera now... " + e);
            }
        }

        if (this.camera.isOpened()) {
            // release the camera
            this.camera.release();
        }
    }

    private void setClosed() {
        this.stopAcquisition();
    }
}
