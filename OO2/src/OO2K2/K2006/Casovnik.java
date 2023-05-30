package OO2K2.K2006;

/**
 * Created by popina on 21.4.15..
 */
public class Casovnik extends Thread {
    private int vreme;
    private char znak;
    private boolean work = false;

    public Casovnik(int vreme, char znak) {
        this.vreme = vreme;
        this.znak = znak;
        start();
    }

    public void run() {
        try {
            while (!interrupted()) {
                synchronized (this) { while (!work) wait(); } // mora while, ako neka nit promeni work
                // synchronized jer wokr moze da se promeni nakon ulaska u wait
                sleep(vreme);
                System.out.print(znak);
            }
        }
        catch (InterruptedException e) {

        }
    }

    public synchronized void Go() {
        work = true; notifyAll();
    }

    public synchronized void Stop() {
        work = false;
    }

    public void Finish() { // ne mora synchronized jer ce za jedan objekat odraditi i nije bitno sta ce ostali odraditi
        interrupt();
    }




}
