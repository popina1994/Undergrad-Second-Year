package OO2K1.K2008.Prodaja;

/**
 * Created by popina on 11.3.15..
 */
public class Sef extends  Radnik {
    private int brPotcinjenih;
    private Radnik[] x;

    public Sef(String ime, double procenat, int ogranicenje) {
        super(ime, procenat);
        x = new Radnik[ogranicenje];
    }

    public boolean Potcini(Radnik r) {
        if ( brPotcinjenih >= x.length)
            return false;
        x[brPotcinjenih++] = r;
        return true;
    }

    public double Prihod() {
        double prihod = 0;
        for (Radnik r : x) {
            if (r != null)
                prihod += r.Prihod();
        }
        return prihod;
    }
}
