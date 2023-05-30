package OO2K1.K2010;
import OO2K1.K2010.Prevoz.*;

/**
 * Created by popina on 14.3.15..
 */
public class Main {
    public static void main(String[] argS) {
        Kamion k = new Kamion("006NU", 3, 100);
        Predmet pr1 = new Predmet("Voda", 20);
        Predmet pr2 = new Predmet("Vatra", 30);
        Predmet pr3 = new Predmet("Vazduh", 40);
        Paket p = new Paket();
        p.DodajTovar(pr2);
        p.DodajTovar(pr3);
        k.Stavi(pr1, 0);
        k.Stavi(p, 1);
        System.out.print(k);

    }
}
