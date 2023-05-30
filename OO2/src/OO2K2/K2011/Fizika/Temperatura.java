package OO2K2.K2011.Fizika;

/**
 * Created by popina on 1.5.15..
 */
public class Temperatura extends Promenljiva {

    public Temperatura(long tMin, long tMax) {
        super(tMin, tMax, 20, 1, -40, 40);
    }

    public String Jedinica() {
        return "oC";
    }
}
