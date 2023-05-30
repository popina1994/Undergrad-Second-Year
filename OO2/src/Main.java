import javax.management.monitor.Monitor;

/**
 * Created by popina on 8.10.15..
 */


public class Main extends Thread {

    public void run()  {
        synchronized (this) {
        notify();}
        System.out.print("Prosao notify");
        try {
            synchronized (this) {
                wait();
            }
        }
        catch (InterruptedException e) {}
        System.out.print("Proslo");

    }

    public static void main(String[] argS) {
        Main m = new Main();
        m.start();

    }
}
