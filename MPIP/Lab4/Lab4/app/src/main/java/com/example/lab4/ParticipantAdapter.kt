package com.example.lab4

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import androidx.recyclerview.widget.RecyclerView

class ParticipantAdapter(
    private val participants: MutableList<Participant>,
    private val onDeleteClick: (Participant) -> Unit
) : RecyclerView.Adapter<ParticipantAdapter.ParticipantViewHolder>() {

    inner class ParticipantViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        private val participantName: TextView = itemView.findViewById(R.id.participantName)
        private val deleteButton: ImageButton = itemView.findViewById(R.id.deleteButton)

        fun bind(participant: Participant) {
        participantName.text=participant.name

        }
    }



    fun updateParticipants(newParticipants: List<Participant>) {
    participants.clear()
        participants.addAll(newParticipants)
        notifyDataSetChanged()
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ParticipantViewHolder {

        val view=LayoutInflater.from(parent.context).inflate(R.layout.item_participant,parent,false)
        return ParticipantViewHolder(view)

    }

    override fun getItemCount(): Int {

        return participants.size
    }

    override fun onBindViewHolder(holder: ParticipantViewHolder, position: Int) {
       holder.bind(participants[position])
    }
}
