package hostelapp.model;
import  lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class Guest {
    private String name;
    private String lastName;

    /*toda primeira linha de um contrutor em java ou é uma chamada recursiva THIS() ou SUPER() (Herança)*/
    public Guest() {
        //this ou super
        this(null);
    }

    private Guest(String name){
        this(name,null);
    }
    public Guest(String name, String lastName) {
        this.name = name;
        this.lastName = lastName;
    }

    public static void main(String[] args) {

        Guest guest = new Guest();

        guest.setName("Pedro");
        guest.setLastName("Henrique");

        System.out.println(guest.getName() + " " + guest.getLastName());

    }
}
