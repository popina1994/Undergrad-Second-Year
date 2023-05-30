package OO2K1.K2009;

import OO2K1.K2009.Igra.*;

/**
 * Created by popina on 12.3.15..
 */
public class Main {
    public static void main(String[] argS) {
        Kutija k = new Kutija();
        Tabla t = new Tabla();
        final int n = 6;
        k.RandomKutija(n);
        System.out.print(k);
        Domina d;
        while ( (d = k.TakeIt()) != null )
            k.Dodaj(d);

        System.out.print(t);
    }
}
