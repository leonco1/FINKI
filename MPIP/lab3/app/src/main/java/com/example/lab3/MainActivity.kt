package com.example.lab3

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.navigation.fragment.NavHostFragment
import com.example.lab3.data.Quotes
import com.example.lab3.data.retrofit.RetrofitInstance
import com.example.lab3.ui.theme.fragments.QuotesFragment
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Initialize the NavController from the NavHostFragment
        val navHostFragment = supportFragmentManager
            .findFragmentById(R.id.fragment_main_container) as NavHostFragment
        val navController = navHostFragment.navController

        if (savedInstanceState == null) {
            val call = RetrofitInstance.apiService.getQuotes()
            call.enqueue(object : Callback<Quotes> {
                override fun onResponse(call: Call<Quotes>, response: Response<Quotes>) {
                    if (response.isSuccessful) {
                        val quote = response.body()
                        val bundle = Bundle()
                        bundle.putSerializable("quotes", quote)

                        val quotesFragment = QuotesFragment()
                        quotesFragment.arguments = bundle

                        navController.navigate(R.id.quotes_fragment,bundle)
                    }
                }

                override fun onFailure(call: Call<Quotes>, t: Throwable) {
                }
            })
        }
    }
}
