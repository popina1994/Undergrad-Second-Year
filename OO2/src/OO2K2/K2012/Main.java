package OO2K2.K2012;
import OO2K2.K2012.Vozovi.*;
/**
 * Created by popina on 1.5.15..
 */
public class Main {
    public static void main(String[] argS) {
        int [] p = new int[] { 5, 10, 15};
        Cenovnik c = new Cenovnik(p);


        Stanica s = new Stanica(c);
        Naplata n = new Naplata("Zarkovo", 3, 100, s);
        n.Start(c);
        try {
            Thread.sleep(1000);
            System.out.print(n + "\n");
            Thread.sleep(1000);
            n.Pause();
            System.out.print(n + "\n");
            n.Stop();
        }
        catch (Exception e) {

        }
    }
}
