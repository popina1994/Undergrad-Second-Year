package OO2K2.K2012.Vozovi;

import OO2K2.K2013.Igraliste.ErrorNijeNiPocela;

/**
 * Created by popina on 1.5.15..
 */
public class Cenovnik {
    private int putarina[];

    public Cenovnik(int putarina[]) {
        this.putarina = putarina;
    }

    public int GetBrKategorija() {
        return putarina.length;
    }

    public int GetPutarina(int kat) throws ErrorNemaKategorija {
        if ( (kat < 0) || (kat >= putarina.length))
            throw new ErrorNemaKategorija();
        return putarina[kat];
    }


}
