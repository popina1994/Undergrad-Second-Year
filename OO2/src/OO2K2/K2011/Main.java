package OO2K2.K2011;

import OO2K2.K2011.Fizika.*;

/**
 * Created by popina on 1.5.15..
 */
public class Main {
    public static void main(String argS[]) {
        final long tMin = 100, tMax = 200, time = 50;
        Temperatura t = new Temperatura(tMin, tMax);
        Pritisak p = new Pritisak(tMin, tMax);
        Merac mT = new Merac(time, t);
        Merac mP = new Merac(time, p);
        try {
            mT.Start();
            mP.Start();
            Thread.sleep(1000);
            mT.Pause();
            mP.Pause();
            System.out.print(mT + "\n");
            System.out.print(mP + "\n");

            mT.Start();
            mP.Start();
            Thread.sleep(1000);
            mT.Stop();
            mP.Stop();
            System.out.print(mT + "\n");
            System.out.print(mP  + "\n");

        }
        catch (Exception e) {
            System.out.print(e);
        }

    }

}
