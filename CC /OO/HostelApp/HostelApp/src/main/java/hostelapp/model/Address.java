package hostelapp.model;
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class Address {
    // Design pattern - Builder
    //Essa implementação não utiliza builder. (SOBRECARGA DE CONSTRUTORES)
    private String address;
    private String zipCode;
    private String city;
    private String state;

    public Address(String address, String zipCode, String city, String state) {
        this.address = address;
        this.zipCode = zipCode;
        this.city = city;
        this.state = state;
    }
    public Address() {
        this(null,null,null,null);
    }


}
