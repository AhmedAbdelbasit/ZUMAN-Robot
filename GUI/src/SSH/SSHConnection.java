package SSH;

import com.jcraft.jsch.*;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class SSHConnection {

    // Create JSch variable
    private JSch jSch = null;
    // Create SSH Session
    private Session session = null;
    // Create new SSH Channel
    private ChannelShell channel = null;

    private InputStream sshInputStream   = null;
    private OutputStream sshOutputStream = null;

    // new SSH Connection
    public boolean openConnection(String host, int port, String username, String password, int timeout) {

        boolean connectionResult = false;

        // Create new value jsch
        this.jSch = new JSch();

        // Set sftp server with no check key at login
        java.util.Properties config = new java.util.Properties();
        config.put("StrictHostKeyChecking", "on");
        this.jSch.setConfig(config);

        try {
            // get session
            this.session = this.jSch.getSession(username, host, port);
            // Set password
            this.session.setPassword(password);

            this.session.connect(timeout);
            // Get channel to connect with ssh server
            this.channel = (ChannelShell) this.session.openChannel("shell");

            //Connect to channel
            this.channel.connect();

            this.sshInputStream = this.channel.getInputStream();
            this.sshOutputStream = this.channel.getOutputStream();

            connectionResult = true;
        } catch (Exception e) {
            // Show error
            e.printStackTrace();
        }

        return connectionResult;
    }

    // function to send commands to ssh server
    public boolean sendCommand(String command) {

        boolean sendResult = false;

        try {
            if (this.sshOutputStream != null) {
                this.sshOutputStream.write(command.getBytes());
                this.sshOutputStream.flush();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return sendResult;
    }

    // function to receive data from ssh server
    public String receiveData() {

        String data = "";

        try {
            if (this.sshInputStream != null) {
                // Check for data from input stream
                int available = this.sshInputStream.available();

                while (available > 0) {
                    byte[] buffer = new byte[available];
                    int byteRead = this.sshInputStream.read(buffer);
                    available = available - byteRead;
                    data += new String(buffer);
                }

                data = data.replace("grad@grad:~$", "");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return data;
    }

    public String replaceCommand(String result, String command) {
        result = result.replace(command, "");
        return result;
    }

    // close function to close all in/out ssh streams
    public void close() {
        if (this.session != null) {
            this.session.disconnect();
        }

        if (this.channel != null) {
            this.channel.disconnect();
        }

        if (this.sshInputStream != null) {
            try {
                this.sshInputStream.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        if (this.sshOutputStream != null) {
            try {
                this.sshOutputStream.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        this.jSch = null;
    }
}
