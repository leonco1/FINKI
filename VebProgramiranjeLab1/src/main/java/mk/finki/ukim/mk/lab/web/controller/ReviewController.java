package mk.finki.ukim.mk.lab.web.controller;

import lombok.AllArgsConstructor;
import mk.finki.ukim.mk.lab.model.Book;
import mk.finki.ukim.mk.lab.model.Review;
import mk.finki.ukim.mk.lab.service.BookService;
import mk.finki.ukim.mk.lab.service.ReviewService;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Optional;

@Controller
@RequestMapping("/review")
@AllArgsConstructor
public class ReviewController {

    private final BookService bookService;
    private final ReviewService reviewService;

    @GetMapping("/{bookId}")
    public String getForm(@PathVariable Long bookId, Model model){
        Optional<Book> book = bookService.findById(bookId);
        if (book.isEmpty()){
            return "redirect:books";
        }
        model.addAttribute("book",book.get());
        return "add-review";
    }

    @PostMapping("/add")
    public String addReviewWithTime(@RequestParam Long bookId,
                                    @RequestParam Integer score,
                                    @RequestParam String description,
                                    @RequestParam(value = "time", required = false)
                                    @DateTimeFormat(iso = DateTimeFormat.ISO.DATE_TIME) LocalDateTime localDateTime){
        if (localDateTime != null){
            reviewService.addReview(bookId,score,description,localDateTime);
        }
        else {
            reviewService.addReview(bookId,score,description);
        }
        return "redirect:/books";
    }

    @GetMapping("/get/{bookId}")
    public String getReviews(@PathVariable Long bookId, Model model){
        Optional<Book> book = bookService.findById(bookId);
        if (book.isEmpty()){
            return "redirect:/books";
        }
        model.addAttribute("book",book.get());
        return "show-review";
    }

    @GetMapping("/search")
    public String getReviews(@RequestParam( value = "from") @DateTimeFormat(iso = DateTimeFormat.ISO.DATE_TIME) LocalDateTime from,
                             @RequestParam(value = "to") @DateTimeFormat(iso = DateTimeFormat.ISO.DATE_TIME) LocalDateTime to,
                             Model model){
        List<Review> results = reviewService.findByTimestampBetween(from,to);
        model.addAttribute("search",true);
        model.addAttribute("searchReviews",results);
        return "show-review";
    }
}
