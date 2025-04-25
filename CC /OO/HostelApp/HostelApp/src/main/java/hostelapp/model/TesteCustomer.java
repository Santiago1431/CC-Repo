package hostelapp.model;

public class TesteCustomer {
    public static void main(String[] args) {
        Guest guest2 = new Guest();

        guest2.setName("Juan");
        guest2.setLastName("Henrique");

        System.out.println(guest2.getName() + " " + guest2.getLastName());
        Address address = new Address("Main Street", "123", "Main Street", "EUA");
        guest2.setAddress(address);
        System.out.println(" \nADDRESS: " + guest2.getAddress().getAddress());
    }
}
