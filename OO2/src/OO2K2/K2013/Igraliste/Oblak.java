package OO2K2.K2013.Igraliste;

/**
 * Created by popina on 29.4.15..
 */
public class Oblak extends  Thread {
    private Livada l;
    private boolean work = false;

    public Oblak(Livada l) {
        this.l = l;
        start();
    }

    public void run() {
        try {
            while (!interrupted()) {

                synchronized (this) {
                    if (!work) wait();
                }
                sleep((int)(Math.random() * 40 + 10));

                try {
                    if (work) {
                        l.PadniKiso((int)(Math.random() * l.duzina()), (int)(Math.random() * l.sirina()), new Kap());
                    }
                }
                catch (ErrorOpseg e) {

                }

            }
        }
        catch (InterruptedException e) {

        }
    }

    public synchronized  void Start() throws ErrorVecPada {
        if (work)
            throw new ErrorVecPada();
        work = true;
        notify();
    }

    public synchronized  void Pause() throws ErrorNijeNiPocela {
        if (!work)
            throw new ErrorNijeNiPocela();
        work = false;
    }

    public void Stop() {
        interrupt();
    }
}
