package OO2K2.K2006;

/**
 * Created by popina on 21.4.15..
 */
public class Znak implements  Uporediv {

    private char znak;

    public Znak(char znak) {
        this.znak = znak;
    }

    public boolean Manji(Uporediv u) {
        return znak < ((Znak)(u)).znak;
    }

    public boolean Jednak(Uporediv u) {
        return znak == ((Znak)(u)).znak;
    }

    public String toString() {
        return "" + znak;
    }
}
