package Threads;

import SSH.SSHApplication;

/**
 * Created by ahmed on 7/14/17.
 */
public class MappingTopic implements Runnable {


    private Thread mapping;
    private SSHApplication sshApplication = null;

    public MappingTopic() {
        mapping = new Thread(this, "Mapping");
        mapping.start();

        sshApplication = new SSHApplication();
        sshApplication.executeCommand("roscore &");
    }

    @Override
    public void run() {

        String output = "";

        sshApplication.executeCommand("rostopic pub ");

        while (!output.contains("arrived")) {
            output = sshApplication.readOutput();
        }
    }
}
