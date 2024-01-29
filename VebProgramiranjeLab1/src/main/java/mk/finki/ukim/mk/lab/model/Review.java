package mk.finki.ukim.mk.lab.model;

import jakarta.persistence.*;
import lombok.Data;
import org.springframework.format.annotation.DateTimeFormat;

import java.time.LocalDateTime;

@Data
@Entity
public class Review {
    @Id @GeneratedValue(strategy = GenerationType.IDENTITY)

    private Long id;
    private Integer score;
    private String description;
    @ManyToOne
    private Book book;
    @DateTimeFormat(iso = DateTimeFormat.ISO.DATE_TIME)
    private LocalDateTime timestamp;

    public Review(Integer score, String description, Book book) {
        this.score = score;
        this.description = description;
        this.book = book;
        this.timestamp = LocalDateTime.now();
    }

    public Review(Integer score, String description, Book book, LocalDateTime timestamp) {
        this.score = score;
        this.description = description;
        this.book = book;
        this.timestamp = timestamp;
    }

    public Review() {

    }
}
