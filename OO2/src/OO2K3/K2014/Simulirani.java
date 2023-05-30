package OO2K3.K2014;

/**
 * Created by popina on 24.8.15..
 */
public class Simulirani extends  Posao {
    private int downTime, upTime;

    public Simulirani(int n, int k, int downTime, int upTime) {
        super(n, k);
        this.downTime = downTime;
        this.upTime = upTime;
    }

    public void Job() throws InterruptedException {
        sleep( (long)(Math.random() * (upTime - downTime)  + downTime));
    }

}
