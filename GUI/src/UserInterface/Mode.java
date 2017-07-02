package UserInterface;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

/**
 * Created by ahmed on 7/1/17.
 */
public class Mode {

    @FXML
    private Button manned_btn;

    @FXML
    private Button auto_btn;

    @FXML
    public void mode(ActionEvent event) throws Exception{

        Stage stage = null;
        Parent root = null;

        if (event.getSource() == manned_btn) {
            stage = (Stage) manned_btn.getScene().getWindow();
            root  = FXMLLoader.load(getClass().getResource("../Layouts/robot_mode.fxml"));
        } else if (event.getSource() == auto_btn) {
            stage = (Stage) auto_btn.getScene().getWindow();
            root  = FXMLLoader.load(getClass().getResource("../Layouts/robot_mode.fxml"));
        }

        assert root != null;
        Scene scene = new Scene(root, 1000, 600);

        assert stage != null;

        stage.setTitle("ZUMAN");
        stage.setScene(scene);
        stage.show();

        Stage finalStage = stage;
        finalStage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            @Override
            public void handle(WindowEvent event) {
                finalStage.close();
            }
        });
    }
}
