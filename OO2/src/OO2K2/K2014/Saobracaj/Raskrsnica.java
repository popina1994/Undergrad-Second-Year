package OO2K2.K2014.Saobracaj;

import java.awt.*;

/**
 * Created by popina on 28.4.15..
 */
public class Raskrsnica extends  Saobracajnica {
    private Ulica u;
    public Raskrsnica(Ulica ulica, long tMin, long tMax) throws ErrorBr {
        super(0, tMin, tMax);
        u = ulica;
        start();
    }

    public void Do() {
        String s = u.Snimak();
        if (s == null)
            System.out.print("Nema nikog\n");
        else
            System.out.print(s + "\n");
    }
}
