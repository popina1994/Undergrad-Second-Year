package OO2K2.K2014.Saobracaj;

/**
 * Created by popina on 28.4.15..
 */
public class Traka {
    private static class Node {
        Vozilo info;
        Node next;

        Node(Vozilo info) {
            this.info = info;
        }
    }

    private Node head, tail;
    private Kamera k;
    private String lastShoot;

    public Traka() {
        k = new Kamera();
    }

    public synchronized void PushBack(Vozilo v) {
        Node tmp = new Node(v);
        if (head == null)
            head = tmp;
        else
            tail.next = tmp;
        tail = tmp;
    }

    public synchronized  Vozilo PopFront() {
        if (head == null) { // empty queue
            lastShoot = null;
            return null;
        }
        Vozilo tmpRet = head.info;
        k.Snimi(tmpRet);
        lastShoot = k.toString();

        head = head.next;
        if (head == null)
            tail = head;
        return tmpRet;
    }


    public synchronized String GetLastShoot() {
        return lastShoot;
    }
}
