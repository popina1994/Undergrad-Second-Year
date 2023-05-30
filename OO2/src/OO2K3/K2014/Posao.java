package OO2K3.K2014;

/**
 * Created by popina on 24.8.15..
 */
public abstract class Posao extends Thread {
    private int n, k;
    private boolean work = false;
    private boolean finished = false;
    private Obavestiva event;

    public Posao(int n, int k) {
        this.n = n; this.k = k;
        work = true;
        start();
    }

    public void Resume() {
        work = true;
        notifyAll();
    }

    public synchronized  void Pause() {
        work = false;
    }

    public synchronized void Stop() {
        interrupt();
    }

    public abstract void Job() throws InterruptedException;

    public void run() {
        try {
            for (int cnt = 0; cnt < n; cnt ++) {
                synchronized (this) {
                    while (!work) {
                        wait();
                    }
                }
                Job();
                if ( (cnt + 1) % k == 0) {
                    if (event != null) {
                        event.Obavesti(k * 100 / n);
                    }
                    System.out.print("Gotov" +  cnt);
                }
            }
        }
        catch (InterruptedException e) {

        }
        finished = true;
    }

    public synchronized String GetState() {
        if (work)
            return "Job is in progress";
        else if (finished)
            return "Job is finished";
        else
            return "Job is paused";
    }



    public void Register(Obavestiva o) throws ErrorMoreEvent {
        if (event != null)
            throw new ErrorMoreEvent();
        event = o;
    }


}
