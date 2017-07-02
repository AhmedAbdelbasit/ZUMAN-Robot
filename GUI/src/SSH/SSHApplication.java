package SSH;

/**
 * Created by ahmed on 6/19/17.
 */
public class SSHApplication {

    private String host     = "192.168.1.103";
    private int port        = 22;
    private String username = "ahmed";
    private String password = "AbdElsalam";
    private int timeout     = 120000;

    private boolean connectionState = false;

    private SSHConnection sshConnection;

    public SSHApplication() {
        sshConnection = new SSHConnection();

        this.connectionState = this.sshConnection.openConnection(
                this.host,
                this.port,
                this.username,
                this.password,
                this.timeout
        );

        if (this.connectionState) {
            System.out.println("Connected Successfully \n");

            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            System.out.println(this.sshConnection.receiveData());
        } else {
            System.out.println("Can't connect \n");
        }
    }

    public void executeCommand(String command) {

        String output;

        this.sshConnection.sendCommand(command + "\n");
        System.out.println(command + "\n");

        try {
            Thread.sleep(500);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        output = this.sshConnection.replaceCommand(this.sshConnection.receiveData(), command);

        System.out.println(output);
    }

    public void exit() {
        this.sshConnection.close();
    }
}
