package mk.finki.ukim.mk.lab.web.controller;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import mk.finki.ukim.mk.lab.service.AuthorService;
import mk.finki.ukim.mk.lab.service.BookService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.thymeleaf.context.WebContext;
import org.thymeleaf.spring6.SpringTemplateEngine;
import org.thymeleaf.web.IWebExchange;
import org.thymeleaf.web.servlet.JakartaServletWebApplication;

import java.io.IOException;

@Controller
@RequestMapping("/bookdetails")
public class BookDetailsController {
    private final AuthorService authorService;
    private final BookService bookService;

    public BookDetailsController(AuthorService authorService, BookService bookService) {
        this.authorService = authorService;
        this.bookService = bookService;
    }

    @GetMapping
    public String getBookDetails(HttpServletRequest request, Model model)
    {
       HttpSession session=request.getSession();
        model.addAttribute("authors",bookService.findBookByIsbn((String) session.getAttribute("isbn")).getAuthors());
        model.addAttribute("book",bookService.findBookByIsbn((String) session.getAttribute("isbn")));
        return "bookdetails";
    }
}
