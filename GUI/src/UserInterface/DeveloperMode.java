package UserInterface;

import SSH.SSHApplication;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

/**
 * Created by ahmed on 7/12/17.
 */
public class DeveloperMode {

    @FXML
    private Button send_btn;

    @FXML
    private Button echo_btn;

    @FXML
    private TextField command_txt;

    @FXML
    private TextField topic_txt;

    @FXML
    private TextArea subbed_txt;

    private SSHApplication sshApplication = null;

    public void initialize() {
        this.sshApplication = new SSHApplication();
    }

    public void sendCommand(ActionEvent actionEvent) {
        String command = command_txt.getText();

        this.sshApplication.executeCommand("roscore &");
        this.sshApplication.executeCommand(command);

    }

    public void echoTopic(ActionEvent actionEvent) {
        String topic = topic_txt.getText();

        this.sshApplication.executeCommand("roscore &");
        this.sshApplication.executeCommand("rostopic echo " + topic);
    }

}
