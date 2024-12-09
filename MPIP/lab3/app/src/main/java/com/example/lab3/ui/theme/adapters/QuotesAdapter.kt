package com.example.lab3.ui.theme.adapters

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.lab3.R
import com.example.lab3.data.Quote
import com.example.lab3.data.Quotes

class QuotesAdapter(private val quotes: Quotes,private val onClick:  (Quote) -> Unit): RecyclerView.Adapter<QuotesAdapter.QuotesViewHolder>() {

    class QuotesViewHolder(quoteView: View,val onClick:(Quote)->Unit):RecyclerView.ViewHolder(quoteView)
    {
        private val quoteIdTextView:TextView=itemView.findViewById(R.id.id)
        private val quoteTextView:TextView=itemView.findViewById(R.id.quote)
        private val authorTextView:TextView=itemView.findViewById(R.id.author)

        private var currentQuote: Quote? = null



        init {
            quoteView.setOnClickListener {
                currentQuote?.let {
                    onClick(it)
                }
            }
        }

        fun bind(quote:Quote)
        {
            currentQuote= quote
            quoteIdTextView.text = quote.id.toString()
            quoteTextView.text = quote.quote
            authorTextView.text = quote.author

        }



    }
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): QuotesViewHolder {
        val view=LayoutInflater.from(parent.context).inflate(R.layout.quotes_row,parent,false)
        return QuotesViewHolder(view,onClick)
    }

    override fun getItemCount(): Int {
        return quotes.quotes.size
    }

    override fun onBindViewHolder(holder: QuotesViewHolder, position: Int) {
        val quote= quotes.quotes[position]

        holder.bind(quote)

    }


}