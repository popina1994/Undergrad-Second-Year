package OO2K2.K2013.Igraliste;

/**
 * Created by popina on 28.4.15..
 */
public class Livada {
    private Busen[][] b;

    public Livada(int numRow, int numCol,Busen b) {
        this.b = new Busen[numRow][numCol];

        for (int idxRow = 0; idxRow < numRow; idxRow++)
            for (int idxCol = 0; idxCol < numCol; idxCol++)
                this.b[idxRow][idxCol] = b.clone();
    }

    public int duzina() {
        return b.length; // nemam pojma sta je duzina, a sta sirina, uzimam nasumicno
    }

    public int sirina() {
        return b[0].length;
    }

    synchronized  public void PadniKiso(int idxRow, int idxCol, Kap k) throws ErrorOpseg {
        if ( (idxRow < 0) || (idxRow >= b.length) || (idxCol < 0) || (idxRow >= b[0].length) )
            throw new ErrorOpseg();

        b[idxRow][idxCol].PadniIbarVodo(k);
    }

    synchronized public void ZastoGori() {
        for (int idxRow = 0; idxRow < b.length; idxRow++)
            for (int idxCol = 0; idxCol < b[0].length; idxCol++)
                b[idxRow][idxCol].IzgoriMiDete();
    }

    synchronized public String toString() {
        String s = "";

        for (int idxRow = 0; idxRow < b.length; idxRow ++) {
            for (int idxCol = 0; idxCol < b[0].length; idxCol++)
                s +=  b[idxRow][idxCol] + " ";
            s += "\n";
        }
        return s;
    }
}
