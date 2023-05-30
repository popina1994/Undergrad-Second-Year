package OO2K1.K2008;

import OO2K1.K2008.Prodaja.*;

/**
 * Created by popina on 11.3.15..
 */
public class Main {
    public static void main(String[] argS) {
       /* Prodavac p1 = new Prodavac("Marko", 10), p2 = new Prodavac("Darko", 20);
        Sef s = new Sef("Slavko", 20, 2);

        s.Potcini(p1);
        s.Potcini(p2);

        Firma f = new Firma(3, 20);
        f.Zaposli(p1);
        f.Zaposli(p2);
        f.Zaposli(s);

        p1.Prodaj(20);
        p2.Prodaj(30);


        System.out.println(f);
*/Firma  firma = new Firma (30, 5);
        Sef      nenad = new Sef      ("Nenad", 6, 3);
        Prodavac marko = new Prodavac ("Marko", 5);
        Prodavac zoran = new Prodavac ("Zoran", 4);
        firma.Zaposli (nenad);
        firma.Zaposli (marko);
        firma.Zaposli (zoran);
        nenad.Potcini  (marko);
        nenad.Potcini  (zoran);
        marko.Prodaj  (5000);
        zoran.Prodaj  (8000);
        System.out.print (firma);
    }

}
