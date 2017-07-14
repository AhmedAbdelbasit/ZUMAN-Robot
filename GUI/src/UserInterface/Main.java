package UserInterface;

import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("../Layouts/mode.fxml"));
        Scene scene = new Scene(root, 1000, 600);

        primaryStage.setTitle("ZUMAN");
        primaryStage.setScene(scene);
        primaryStage.show();

        primaryStage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            @Override
            public void handle(WindowEvent event) {
                primaryStage.close();
            }
        });
    }

    public static void main(String[] args) {
        // The absolute path of "libopencv_java320.so" inside "lib" folder between brackets
        System.load("/media/ahmed/BEFE53D5FE538495/College/CSE2017/Graduation Project/ZumanUI/lib/libopencv_java320.so");
        launch(args);
    }
}
