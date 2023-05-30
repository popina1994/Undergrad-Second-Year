package OO2K1.K2011;
import OO2K1.K2011.galerija.*;

public class Main {
    public static void main(String [] argS) {
        Slika s1 = new Slika("mama", 1, 1);
        Slika s2 = new Slika("tata", 1, 1);
        Film f = new Film("porodica", 2);

        f.Dodaj(s1);
        f.Dodaj(s2);
        Slika s = new Slika("dete", 2, 3);

        Galerija g = new Galerija(3);
        g.Dodaj(0, f);
        g.Dodaj(1, s);
        System.out.print(g);
    }
}
