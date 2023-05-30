package OO2K3.K2014;

/**
 * Created by popina on 24.8.15..
 */
public class ErrorMoreEvent extends Exception {
    public String toString() {
        return "More than one event was tried to register";
    }
}
