package com.example.lab3.ui.theme.fragments

import android.annotation.SuppressLint
import android.os.Bundle
import android.util.Log
import android.view.View
import androidx.fragment.app.Fragment
import androidx.navigation.fragment.navArgs
import com.example.lab3.R
import com.example.lab3.databinding.FragmentQuoteBinding

class QuoteDetailsFragment:Fragment(R.layout.fragment_quote) {

    private var _binding: FragmentQuoteBinding?=null
    private val binding get()=_binding!!
    private val args:QuoteDetailsFragmentArgs by navArgs()

    @SuppressLint("SetTextI18n")
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        _binding=FragmentQuoteBinding.bind(view)
        Log.d("QuoteDetailsFragment", "TextView ID is: ${binding.id}, TextView Quote is: ${binding.quote}, TextView Author is: ${binding.author}")
        binding.apply { id.text=args.selectedQuote.id.toString()
        quote.text=args.selectedQuote.quote
        author.text=args.selectedQuote.author}



    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }

}