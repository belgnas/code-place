
class NoGasException extends Exception {
    public NoGasException(String message) {
        super(message);
    }
}

class Kitchen {
    public void cook() throws NoGasException{
        throw new NoGasException("没煤气了喵！");
    }
}

class Main_day13 {
    public static void main(String[] args) {
        Kitchen kitchen = new Kitchen();

        try {
            kitchen.cook();
        }
        catch (NoGasException e) {
            System.out.println(e.getMessage());
            System.out.println("没事，本喵改用电磁炉做饭！");
        }
    }
}
