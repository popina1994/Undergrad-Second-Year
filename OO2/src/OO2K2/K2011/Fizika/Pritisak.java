package OO2K2.K2011.Fizika;

/**
 * Created by popina on 1.5.15..
 */
public class Pritisak extends  Promenljiva {
    public Pritisak(long tMin, long tMax) {
        super(tMin, tMax, 1000, 5, 900, 1100);
    }

    public String Jedinica() {
        return "mbar";
    }
}
