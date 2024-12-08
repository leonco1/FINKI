package com.example.notesapp

import android.annotation.SuppressLint
import android.os.Bundle
import android.provider.ContactsContract.CommonDataKinds.Note
import com.google.android.material.snackbar.Snackbar
import androidx.appcompat.app.AppCompatActivity
import androidx.navigation.findNavController
import androidx.navigation.ui.AppBarConfiguration
import androidx.navigation.ui.navigateUp
import androidx.navigation.ui.setupActionBarWithNavController
import android.view.Menu
import android.view.MenuItem
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import androidx.core.widget.addTextChangedListener
import androidx.lifecycle.ViewModelProvider
import com.example.notesapp.viewmodels.NotesViewModel

class MainActivity : AppCompatActivity() {
private lateinit var textViewNotes:TextView
private lateinit var editTextNotes:EditText
private lateinit var notesViewModel:NotesViewModel
private lateinit var btnSubmitNotes: Button
    @SuppressLint("MissingInflatedId")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.notes_layout)

        textViewNotes = findViewById(R.id.tvNote)
        editTextNotes = findViewById(R.id.etNote)
        btnSubmitNotes = findViewById(R.id.btnSave)
        notesViewModel=ViewModelProvider(this)[NotesViewModel::class.java]
//
//        editTextNotes.addTextChangedListener{
//            newText->notesViewModel.setUserText(newText.toString())
//        }
        notesViewModel.getUserTextValue().observe(this)
        {
            textViewNotes.text=notesViewModel.getUserText()
        }
        btnSubmitNotes.setOnClickListener{
            notesViewModel.setUserText(editTextNotes.text.toString())
        }

    }
}