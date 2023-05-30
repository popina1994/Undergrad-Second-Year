package OO2K1.K2012.Muzika;

/**
 * Created by popina on 21.3.15..
 */
public class Knjiga extends Stavka {
    private String [] autori;

    public Knjiga(String naslov, String izdavac, String[] autori) {
        super(naslov, izdavac);
        this.autori = autori;
    }

    public char GetVrsta() {
        return 'K';
    }

    public String toString() {
        String s = super.toString() + "[";
        for (String aut : autori)
            if (aut != autori[0])
                s += ", " + aut;
            else
                s += aut;
        return s + "]";
    }

}
