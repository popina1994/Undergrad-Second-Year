package OO2K2.K2013.Igraliste;

/**
 * Created by popina on 28.4.15..
 */
public class Busen implements Merljiv, Cloneable {
    private int vUk;
    public void PadniIbarVodo(Kap k) {
        vUk += k.Zapremina();
    }

    public int Zapremina() {
        return vUk;
    }

    public void IzgoriMiDete() {
        vUk = 0;
    }

    public Busen clone() {
        try {
            Busen b = (Busen)(super.clone());
            return b;
        }
        catch (CloneNotSupportedException c) {
            return null; // nema memorije?
        }
    }

    public String toString() {
        return "" + vUk;
    }
}
