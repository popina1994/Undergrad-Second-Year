package OO2K3.K2014;

/**
 * Created by popina on 24.8.15..
 */
public class Main {
    public  static void main(String[] argS) {
        Simulirani s = new Simulirani(10, 1, 950, 1000);
        try {
            Thread.sleep(3000);
        }
        catch (InterruptedException e) {

        }
        s.Stop();
    }
}
