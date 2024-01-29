package mk.finki.ukim.mk.lab.model;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import org.hibernate.annotations.OnDelete;
import org.hibernate.annotations.OnDeleteAction;

import java.util.ArrayList;
import java.util.List;

@Data
@Entity
@Table(name = "books")
public class Book {
    String isbn;
    @Id@GeneratedValue(strategy = GenerationType.IDENTITY)
    Long id;
    String title;
    String genre;
    int year;
    @ManyToMany(cascade = CascadeType.MERGE)
    @JoinTable(
            name = "book_authors",
            joinColumns = @JoinColumn(name = "book_id"),
            inverseJoinColumns = @JoinColumn(name = "author_id"),
            foreignKey = @ForeignKey(name = "fk_book_author_book", foreignKeyDefinition = "FOREIGN KEY (book_id) REFERENCES books(id) ON DELETE CASCADE"),
            inverseForeignKey = @ForeignKey(name = "fk_book_author_author", foreignKeyDefinition = "FOREIGN KEY (author_id) REFERENCES authors(id) ON DELETE CASCADE")
    )    List<Author> authors;
    @ManyToOne
    @JoinColumn(name = "bookstore_id")
    private BookStore bookStore;
    @OneToMany(mappedBy = "book")
    private List<Review> reviews;
        @ManyToOne
        private BookSales bookSales;

    public Book() {
    }

    public Book(String isbn, String title, String genre, int year, List<Author> authors, BookStore bookStore,BookSales bookSales) {
        this.isbn = isbn;
        this.title = title;
        this.genre = genre;
        this.year = year;
        this.authors = authors;
        this.bookStore = bookStore;
        this.bookSales=bookSales;
    }

    public Book(String isbn, String title, String genre, Integer year, BookStore bookStore) {

    }
    public Book(String isbn, String title, String genre, int year, List<Author> authors, BookStore bookStore) {
        this.isbn = isbn;
        this.title = title;
        this.genre = genre;
        this.year = year;
        this.authors = authors;
        this.bookStore = bookStore;
    }
}
