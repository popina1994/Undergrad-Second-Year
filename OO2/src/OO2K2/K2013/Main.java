package OO2K2.K2013;

import OO2K2.K2013.Igraliste.*;

/**
 * Created by popina on 28.4.15..
 */
public class Main {
    public static void main(String[] argS) {
        Livada l = new Livada(4, 5, new Busen());
        Oblak o = new Oblak(l);
        try {
            o.Start();

            Thread.sleep(5000);
            System.out.print(l);
            Thread.sleep(3000);
            o.Pause();
            System.out.print(l);
            l.ZastoGori();
            System.out.print(l);
            o.Pause();

        }
        catch (ErrorNijeNiPocela e) {
            System.out.print("Sunce li ti, sta li si zeznuo :D ?");
            o.Stop();
        }
        catch (ErrorVecPada e) {
            System.out.print("Opet si nesto popio");
            o.Stop();
        }
        catch (InterruptedException e) {

        }
        o.Stop();
    }
}
