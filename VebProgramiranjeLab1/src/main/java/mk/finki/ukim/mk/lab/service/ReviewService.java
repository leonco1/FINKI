package mk.finki.ukim.mk.lab.service;

import mk.finki.ukim.mk.lab.model.Review;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Optional;

public interface ReviewService {
    Optional<Review> addReview(Long bookId, Integer score, String description);
    Optional<Review> addReview(Long bookId, Integer score, String description, LocalDateTime localDateTime);
    List<Review> findByTimestampBetween(LocalDateTime from, LocalDateTime to);
}