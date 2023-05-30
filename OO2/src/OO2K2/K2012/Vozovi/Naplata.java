package OO2K2.K2012.Vozovi;

/**
 * Created by popina on 1.5.15..
 */
public class Naplata extends Thread {
    private String naziv;
    private long tSr;
    private boolean work = false;
    private Stanica[] s;
    private Cenovnik c;


    public Naplata(String naziv, int brStanica, long tSr, Stanica sCopy) {
        this.naziv = naziv;
        this.tSr = tSr;
        s = new Stanica[brStanica];
        for (int idx = 0; idx < brStanica; idx ++)
            s[idx] = sCopy.clone();
        start();
    }

    public synchronized void Start(Cenovnik c) {
        work = true;
        for (Stanica st : s) {
            st.SetCenovnik(c);
            this.c = c;
        }
    }

    public synchronized void Pause() {
        work = false;
    }

    public void Stop() {
        interrupt();
    }

    public void run() {
        try {
            while (!interrupted()) {
                synchronized (this) {
                    while (!work) wait();
                }

                sleep(tSr + (int)(Math.random() * tSr * 0.3));
                synchronized (this) {
                    if (work) {
                        Vozilo v = new Vozilo((int)(Math.random() * c.GetBrKategorija()));
                        try {
                            s[(int) (Math.random() * s.length)].NaplatiPutarinu(v);
                        }
                        catch (Exception e) {

                        }
                    }
                }

            }
        }
        catch (InterruptedException e) {

        }

    }

    public synchronized int Naplaceno() { // izracuna koliko je naplaceno i to vrati na izlaz
        int naplaceno = 0;

        for (Stanica st : s) {
            naplaceno += st.GetPutarina();
        }
        return naplaceno;
    }

    public String toString() {
        String str = naziv + "(" + Naplaceno() + "):";

        for (int idx = 0; idx < s.length; idx ++) {
            if (idx != 0)
                str += ", ";
            str += s[idx];

        }
        return str;
     }
}
