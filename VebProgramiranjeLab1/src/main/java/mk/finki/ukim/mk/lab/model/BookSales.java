package mk.finki.ukim.mk.lab.model;

import jakarta.persistence.*;
import lombok.Data;
import org.springframework.data.repository.cdi.Eager;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDate;
import java.util.List;

@Data
@Entity
@Table(name="BookSales")

public class BookSales {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    Long id;
    private Integer copies_sold;
    @DateTimeFormat(pattern = "dd-MM-yyyy")
    private LocalDate date;
    @OneToMany(mappedBy = "bookSales")
    private List<Book> bookSold;

    public BookSales(int i) {
        this.copies_sold=i;
        this.date=LocalDate.now();
    }
    public BookSales()
    {}

}
