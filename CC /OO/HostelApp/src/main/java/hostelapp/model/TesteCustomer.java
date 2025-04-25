package hostelapp.model;

public class TesteCustomer {
    public static void main(String[] args) {
        Guest guest2 = new Guest();

        guest2.setName("Juan");
        guest2.setLastName("Henrique");

        System.out.println(guest2.getName() + " " + guest2.getLastName());
    }
}
