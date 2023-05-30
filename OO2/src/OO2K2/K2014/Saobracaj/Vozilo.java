package OO2K2.K2014.Saobracaj;

/**
 * Created by popina on 25.4.15..
 */
public class Vozilo implements Registrovano {
    private String oznaka = new String("");

    public Vozilo() {
        int broj = (int)(Math.random() * 3);
        if (broj == 0)
            oznaka += "BG";
        else if (broj == 1)
            oznaka += "NS";
        else
            oznaka += "NI";

        oznaka += (int) (Math.random()*899+ 100);
    }

    public String RegOznaka() {
        return oznaka;
    }

}
