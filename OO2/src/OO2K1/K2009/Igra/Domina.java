package OO2K1.K2009.Igra;

/**
 * Created by popina on 12.3.15..
 */
public class Domina {
    private int a, b;

    public Domina(int a, int b) {
        this.a = a;
        this.b = b;
    }

    public void Reverse() {
        int tmp = a;
        a = b;
        b = tmp;
    }

    public int GetFirst() {
        return a;
    }

    public int GetSecond() {
        return b;
    }

    public void Swap() {
        int tmp = a;
        a = b;
        b = tmp;
    }

    public boolean Equal(Domina d) {
        if ( ( (a == d.a) && (b == d.b) ) || ( (a == d.b) && (b == d.a) ) )
            return true;
        return false;
    }

    public String toString() {
        return "(" + a + ", " + b + ")";
    }

}
