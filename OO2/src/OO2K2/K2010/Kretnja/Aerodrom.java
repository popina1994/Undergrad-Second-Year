package OO2K2.K2010.Kretnja;

/**
 * Created by popina on 3.5.15..
 */
public class Aerodrom {
    public final static int AUTO = 1;
    public final static int SUDAR_SA_DUZINOM = 2;
    public final static int SUDAR_SA_SIRINOM = 3;
    private int width, length;
    private Automobil [] a;
    private int lastIdx;


    public Aerodrom(int width, int length, int cap) {
        this.width = width;
        this.length = length;
        a = new Automobil[cap];
    }

    public Automobil Dohvati(int idx) throws ErrorOutOfBounds {
        if ( (idx < 0) || (idx >= a.length))
            throw new ErrorOutOfBounds();
        return a[idx];
    }

    public void Dodaj(Automobil auto) throws ErrorPun {
        if (lastIdx >= a.length)
            throw new ErrorPun();
        a[lastIdx++] = auto;
        auto.Start();
    }

    public int IsCrashed(Automobil a) {
        return 1;
    }


}
