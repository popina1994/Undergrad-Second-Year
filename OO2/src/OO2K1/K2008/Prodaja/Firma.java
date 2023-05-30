package OO2K1.K2008.Prodaja;

/**
 * Created by popina on 11.3.15..
 */
public class Firma {
    private int zaposleno;
    private double marza;
    private Radnik [] x;

    public Firma(int brojRadnih, double marza) {
        this.marza = marza;
        x = new Radnik[brojRadnih];
    }

    public boolean Zaposli(Radnik r) {
        if ( (r == null) || (zaposleno == x.length) )
            return false;

        for (int idx = 0; idx < x.length; idx ++)
            if (x[idx] == null) {
                x[idx] = r;
                break;
            }
        zaposleno++;
        return true;
    }

    public boolean Otpusti(int idx) {
        if ( (idx < 0) || (idx >= x.length))
            return false;
        x[idx] = null;
        zaposleno --;
        return true;
    }



    public double Dobit() {
        double plata = 0, zarada = 0;
        for (Radnik r : x) {
            if (r != null)
                plata += r.Plata();
            if ( (r != null) && (r instanceof  Prodavac) )
                zarada += r.Prihod();
        }
        zarada = zarada * marza / 100;
        return zarada - plata;
    }

    public String toString() {
        String s = "";
        for (Radnik r : x) {
            if (x != null)
                s += r;

            s += "\n";
        }
        s += Dobit() + "\n";
        return s;
    }

}
