package OO2K2.K2006;

/**
 * Created by popina on 25.4.15..
 */
public abstract class Uredjivac {
    private Casovnik c;

    public Uredjivac(Casovnik c) {
        this.c = c;
    }

    public void Uredi(Uporediv[] u) {
        c.Go();
        Radi(u);
        c.Stop();
    }

    protected abstract void Radi(Uporediv[] u);

}
