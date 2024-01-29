package mk.finki.ukim.mk.lab.service.impl;

import lombok.AllArgsConstructor;
import mk.finki.ukim.mk.lab.model.Book;
import mk.finki.ukim.mk.lab.model.Review;
import mk.finki.ukim.mk.lab.repository.jpa.BookRepository;
import mk.finki.ukim.mk.lab.repository.jpa.ReviewRepository;
import mk.finki.ukim.mk.lab.service.ReviewService;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Optional;

@Service
@AllArgsConstructor
 class ReviewServiceImpl implements ReviewService {
    private final BookRepository bookRepository;
    private final ReviewRepository reviewRepository;
    @Override
    public Optional<Review> addReview(Long bookId, Integer score, String description) {
        Optional<Book> book = bookRepository.findById(bookId);
        return book.map(value -> Optional.of(reviewRepository.save(new Review(score, description, value)))).orElse(null);
    }

    @Override
    public Optional<Review> addReview(Long bookId, Integer score, String description, LocalDateTime localDateTime) {
        Optional<Book> book = bookRepository.findById(bookId);
        return book.map(value -> Optional.of(reviewRepository.save(new Review(score, description, value,localDateTime)))).orElse(null);
    }

    @Override
    public List<Review> findByTimestampBetween(LocalDateTime from, LocalDateTime to) {
        return reviewRepository.findByTimestampBetween(from,to);
    }
}
