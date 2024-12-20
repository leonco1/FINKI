package com.example.lab4

import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.lab4.databinding.ActivityMainBinding
import kotlinx.coroutines.*

class MainActivity : AppCompatActivity() {
    private lateinit var binding: ActivityMainBinding
    private lateinit var database: ParticipantDatabase
    private lateinit var participantDao: ParticipantDao
    private lateinit var adapter: ParticipantAdapter
    private val participants = mutableListOf<Participant>()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

         adapter=ParticipantAdapter(participants){
            participant->deleteParticipant(participant)
        }
        database=ParticipantDatabase.getDatabase(this)
        participantDao=database.participantDao()


        binding.recyclerView.layoutManager=LinearLayoutManager(this)
        binding.recyclerView.adapter=adapter



        binding.addButton.setOnClickListener {
            val name = binding.editText.text.toString()
            if (name.isNotEmpty())
            {
                val newParticipant:Participant=Participant(name=name)
                addParticipant(newParticipant)
                binding.editText.text.clear()
            }
        }

        binding.assignButton.setOnClickListener { assignSecretSantas() }
        fetchParticipants()
    }

    private fun fetchParticipants() {
        CoroutineScope(Dispatchers.IO).launch {
            val allParticipants = participantDao.getAllParticipants()
            withContext(Dispatchers.Main) {
               adapter.updateParticipants(allParticipants)
            }
        }
    }

    private fun addParticipant(participant: Participant) {

        CoroutineScope(Dispatchers.IO).launch {

            participantDao.insertParticipant(participant)
            fetchParticipants()
        }
    }

    private fun deleteParticipant(participant: Participant) {
        CoroutineScope(Dispatchers.IO).launch {
            participantDao.deleteParticipant(participant)
            fetchParticipants()
        }
    }

    private fun assignSecretSantas() {
     if(participants.size<2)
     {
         AlertDialog.Builder(this).setTitle("NotEnoughParticipantsError").setMessage("At least 2 participants are required")
             .setPositiveButton("Ok",null).show()
         return
     }

        val shuffledList = participants.shuffled()
        val assignments = shuffledList.zipWithNext() + Pair(shuffledList.last(), shuffledList.first())

        val message = assignments.joinToString("\n") { "${it.first.name} -> ${it.second.name}" }
        val alertDialog = AlertDialog.Builder(this)
            .setTitle("Secret Santa Assignments")
            .setMessage(message)
            .setPositiveButton("OK", null)
            .create()

        alertDialog.setOnShowListener{
            alertDialog.window?.setBackgroundDrawableResource(R.color.background_red)
            val titleView = alertDialog.findViewById<TextView>(android.R.id.title)
            titleView?.setTextColor(ContextCompat.getColor(this, R.color.primary_red))
            val messageView = alertDialog.findViewById<TextView>(android.R.id.message)
            messageView?.setTextColor(ContextCompat.getColor(this, R.color.primary_red))
            alertDialog.getButton(AlertDialog.BUTTON_POSITIVE).apply {
                setTextColor(ContextCompat.getColor(this@MainActivity, android.R.color.holo_red_light))
            }
        }
        alertDialog.show()
    }
}
