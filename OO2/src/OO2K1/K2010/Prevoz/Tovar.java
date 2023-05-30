package OO2K1.K2010.Prevoz;

/**
 * Created by popina on 14.3.15..
 */
public abstract class Tovar {
    protected String vrsta;

    Tovar(String vrsta) {
        this.vrsta = vrsta;
    }

    public abstract String GetVrsta();
    public abstract double GetTezina();
    public String toString() {
        return GetVrsta() + "(" + GetTezina() + ")";
    }
}
