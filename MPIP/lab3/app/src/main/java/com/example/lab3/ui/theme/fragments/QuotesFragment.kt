package com.example.lab3.ui.theme.fragments

import android.os.Bundle
import android.view.View
import androidx.fragment.app.Fragment
import androidx.navigation.fragment.findNavController
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.lab3.R
import com.example.lab3.data.Quotes
import com.example.lab3.databinding.FragmentMainBinding
import com.example.lab3.ui.theme.adapters.QuotesAdapter


class QuotesFragment : Fragment(R.layout.fragment_main) {
    private var _binding: FragmentMainBinding? = null
    private val binding get() = _binding!!

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        _binding = FragmentMainBinding.bind(view)

        binding.rQuotes.layoutManager = LinearLayoutManager(context)

        val quotes = arguments?.getSerializable("quotes") as? Quotes

        if (quotes != null) {
            val adapter = QuotesAdapter(quotes) { quote ->
                val action = QuotesFragmentDirections.quotesFragmentToQuoteDetailsFragment(quote)
                findNavController().navigate(action)
            }
            binding.rQuotes.adapter = adapter
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}
