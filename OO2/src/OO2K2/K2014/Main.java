package OO2K2.K2014;
import OO2K2.K2014.Saobracaj.*;

/**
 * Created by popina on 25.4.15..
 */
public class Main {
    public static void main(String[] argS) {
        long minT = 10;
        long maxT = 30;

        try {
            Ulica u = new Ulica(5, minT, maxT);
            Raskrsnica r = new Raskrsnica(u, minT, maxT);
            u.Start();
            r.Start();
            Thread.sleep(3000);
            u.Pause();
            r.Pause();
            u.Stop();
            r.Stop();
        }
        catch (Exception g) {
            System.out.print(g);
        }
    }
}
