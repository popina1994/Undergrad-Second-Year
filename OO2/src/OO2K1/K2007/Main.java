package OO2K1.K2007;

public class Main {
    public static void main(String[] argS) {
        Potrosac[] p = {new Uredjaj("Pegla", 200), new Uredjaj("Sporet", 100), new Uredjaj("fen", 1000)};
        Grupa g = new Grupa();

        Izvor i = new Izvor(1000, 3);
        int idx = 0;
        for (Potrosac potr : p) {
            i.Prikljuci(potr, idx);
            idx++;
        }

        System.out.println(i);


    }
}
